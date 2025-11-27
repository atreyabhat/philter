#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: ./scan.sh <filename>"
  exit 1
fi

FILE="$1"
URL="http://localhost:8787/scan"

# Read file content and escape for JSON
CONTENT=$(cat "$FILE" | python3 -c 'import json,sys; print(json.dumps(sys.stdin.read()))')

# Construct JSON payload
JSON_PAYLOAD="{\"text\": $CONTENT}"

echo "Scanning $FILE..."
echo "Sending request to $URL..."

curl -X POST "$URL" \
     -H "Content-Type: application/json" \
     -d "$JSON_PAYLOAD" | python3 -m json.tool
