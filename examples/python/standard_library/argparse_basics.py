# Compile: python3 argparse_basics.py
# Output:
# Input: data.csv
# Workers: 8
# Verbose: True

import argparse

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Process files with configurable workers",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("input",  help="Input file path")
    parser.add_argument("-o", "--output", default="output.json", help="Output file")
    parser.add_argument("-w", "--workers", type=int, default=4, metavar="N")
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument(
        "--log-level",
        choices=["debug", "info", "warning", "error"],
        default="info",
    )
    return parser

args = build_parser().parse_args(["data.csv", "-w", "8", "--verbose"])
print(f"Input: {args.input}")
print(f"Workers: {args.workers}")
print(f"Verbose: {args.verbose}")
print(f"Output: {args.output}")
print(f"Log level: {args.log_level}")
