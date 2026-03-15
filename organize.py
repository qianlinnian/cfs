"""
Organize Codeforces solution files into contest folders.

Reads .prob files from .cph/ directory, extracts the contest name,
and moves .cpp + .prob files into contest-named subfolders.
Also updates srcPath in .prob files so CPH continues to work.

Usage: python organize.py [--dry-run]
"""

import hashlib
import json
import os
import re
import shutil
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
CPH_DIR = os.path.join(ROOT, ".cph")


def extract_contest_folder_name(group: str) -> str:
    """Convert group string to a clean folder name.

    Examples:
        "Codeforces - Codeforces Round 1076 (Div. 3)" -> "1076-Div3"
        "Codeforces - Educational Codeforces Round 178 (Rated for Div. 2)" -> "Edu178-Div2"
        "Codeforces - Kotlin Heroes: Episode 12" -> "Kotlin-Heroes-Episode-12"
    """
    # Remove the "Codeforces - " prefix
    name = re.sub(r"^Codeforces\s*-\s*", "", group)

    # Educational round
    m = re.match(r"Educational Codeforces Round (\d+).*?Div\.\s*(\d+)", name)
    if m:
        return f"Edu{m.group(1)}-Div{m.group(2)}"

    # Standard Codeforces Round
    m = re.match(r"Codeforces Round (\d+)\s*\(Div\.\s*(\d+)\)", name)
    if m:
        return f"{m.group(1)}-Div{m.group(2)}"

    # Fallback: clean up special characters
    name = re.sub(r"[^\w\s-]", "", name)
    name = re.sub(r"\s+", "-", name.strip())
    return name


def to_cph_path(path: str) -> str:
    """Convert path to CPH's format: lowercase drive letter + backslashes."""
    p = os.path.normpath(path)
    if len(p) >= 2 and p[1] == ":":
        p = p[0].lower() + p[1:]
    return p


def make_prob_filename(src_path: str) -> str:
    """Generate the .prob filename the same way CPH does: .{basename}_{md5(full_path)}.prob"""
    cph_path = to_cph_path(src_path)
    basename = os.path.basename(cph_path)
    md5_hash = hashlib.md5(cph_path.encode()).hexdigest()
    return f".{basename}_{md5_hash}.prob"


def find_prob_files():
    """Find all .prob files and return their parsed data with file paths."""
    results = []
    if not os.path.isdir(CPH_DIR):
        return results

    for fname in os.listdir(CPH_DIR):
        if not fname.endswith(".prob"):
            continue
        prob_path = os.path.join(CPH_DIR, fname)
        with open(prob_path, "r", encoding="utf-8") as f:
            data = json.load(f)
        results.append({"prob_path": prob_path, "prob_name": fname, "data": data})
    return results


def organize(dry_run=False):
    probs = find_prob_files()
    if not probs:
        print("No .prob files found in .cph/")
        return

    moved = 0
    skipped = 0

    for item in probs:
        data = item["data"]
        group = data.get("group", "")
        src_path = data.get("srcPath", "")

        if not group or not src_path:
            print(f"  SKIP (no group/srcPath): {item['prob_name']}")
            skipped += 1
            continue

        cpp_name = os.path.basename(src_path)
        current_cpp = os.path.join(ROOT, cpp_name)

        # Only process files that are in the root directory
        src_dir = os.path.normcase(os.path.normpath(os.path.dirname(src_path)))
        root_norm = os.path.normcase(os.path.normpath(ROOT))
        if src_dir != root_norm:
            # Already in a subfolder, check if .prob is also there
            contest_dir = os.path.dirname(src_path)
            target_cph = os.path.join(contest_dir, ".cph")
            target_prob = os.path.join(target_cph, item["prob_name"])
            if not os.path.exists(target_prob) and os.path.exists(item["prob_path"]):
                # .prob still in root .cph, move it
                folder_name = extract_contest_folder_name(group)
                print(f"  MOVE .prob: {item['prob_name']} -> {folder_name}/.cph/")
                if not dry_run:
                    os.makedirs(target_cph, exist_ok=True)
                    shutil.move(item["prob_path"], target_prob)
                moved += 1
            else:
                skipped += 1
            continue

        if not os.path.exists(current_cpp):
            print(f"  SKIP (cpp not found): {cpp_name}")
            skipped += 1
            continue

        folder_name = extract_contest_folder_name(group)
        contest_dir = os.path.join(ROOT, folder_name)
        target_cpp = os.path.join(contest_dir, cpp_name)
        target_cph = os.path.join(contest_dir, ".cph")
        target_prob = os.path.join(target_cph, item["prob_name"])

        print(f"  {cpp_name} -> {folder_name}/")

        if not dry_run:
            os.makedirs(contest_dir, exist_ok=True)
            os.makedirs(target_cph, exist_ok=True)

            # Move .cpp file
            shutil.move(current_cpp, target_cpp)

            # Update srcPath and rename .prob with new hash so CPH can find it
            data["srcPath"] = to_cph_path(target_cpp)
            new_prob_name = make_prob_filename(target_cpp)
            target_prob = os.path.join(target_cph, new_prob_name)
            with open(item["prob_path"], "w", encoding="utf-8") as f:
                json.dump(data, f, ensure_ascii=False)
            shutil.move(item["prob_path"], target_prob)

        moved += 1

    print(f"\nDone: {moved} moved, {skipped} skipped")
    if dry_run:
        print("(dry-run mode, no files were actually moved)")


if __name__ == "__main__":
    dry_run = "--dry-run" in sys.argv
    print(f"Organizing solutions in: {ROOT}")
    print(f"Dry run: {dry_run}\n")
    organize(dry_run)
