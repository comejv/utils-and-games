#!/bin/bash

# Exit immediately on error
set -e

# Get repository URL and shift the arguments
rurl="$1"
shift 1

# Extract the directory name from the repository URL
dirname=$(basename "${rurl%.git}")

if [ ! -d "$dirname" ]; then
  # If the directory doesn't exist, clone the repository and initialize sparse checkout
  git clone --filter=blob:none --no-checkout "$rurl" "$dirname"
  cd "$dirname"
  git sparse-checkout init --cone
  git checkout HEAD

  checkoutarg="set"
else
  cd "$dirname"
  checkoutarg="add"
fi

# Add the specified files, if any
if [ $# -gt 0 ]; then
  git sparse-checkout "$checkoutarg" "$@"
else
  echo "No folders given. Nothing to checkout."
fi

echo "Done, sparse-cloned $dirname."
