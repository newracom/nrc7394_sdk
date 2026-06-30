#!/bin/sh

if [ $# -ne 2 ]; then
	echo "Usage: $0 <fw_path> <version>"
	echo "Example: $0 out/.../nrc7394_standalone_xip_sample_smart_conn_4M.bin 1.1.0"
	exit 1
fi

fw_path="$1"
version="$2"
fw_name="$(basename "$fw_path")"

out_json=/tmp/fota-version.json

python3 - <<'PY' "$fw_path" "$fw_name" "$version" "$out_json"
import sys, zlib, json

fw_path  = sys.argv[1]
fw_name  = sys.argv[2]
version  = sys.argv[3]
out_path = sys.argv[4]

with open(fw_path, "rb") as f:
	data = f.read()

crc = zlib.crc32(data) & 0xffffffff

obj = {
	"version": version,
	"crc": f"{crc:08x}",
	"force": "0",
	"fw_name": fw_name,
}

with open(out_path, "w", encoding="utf-8") as out:
	json.dump(obj, out, indent=4)
	out.write("\n")

print(f"Wrote {out_path}")
PY

cat "$out_json"
