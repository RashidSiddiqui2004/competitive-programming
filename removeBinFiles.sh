#!/bin/bash

# This script removes all .bin files from the specified directory and its subdirectories.

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <target_directory>"
    exit 1
fi

TARGET_DIR="$1"

# Check if the target directory actually exists
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory does not exist."
    exit 1
fi

# If no .bin files are found, inform the user and exit
if ! find "$TARGET_DIR" -type f -name "*.bin" | grep -q .; then
    echo "No .bin files found in $TARGET_DIR."
    exit 0
fi

# List all .bin files that will be removed
echo "The following .bin files will be removed:"
echo "------------------------------------------------"
find "$TARGET_DIR" -type f -name "*.bin"

echo ""

# Confirm with the user before proceeding
read -p "Are you sure you want to delete these files? (y/n): " choice

if [ "$choice" = "y" ]; then
    echo "Continuing..."

    # Find and remove all .bin files in the target directory and its subdirectories
    find "$TARGET_DIR" -type f -name "*.bin" -delete

    echo "All .bin files have been removed from $TARGET_DIR and its subdirectories."
else
    echo "Operation cancelled."
fi

exit 0