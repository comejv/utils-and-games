# Sparse cloning
A script that allows you to clone a git repository without downloading all files and folders. This is useful if you only need a few files from a large repository.

Usage : `./sparse-checkout.sh <repo-ref> <path1> <path2> ...`
repo-ref can be a URL or a ssh reference to a git repository.
path1, path2, ... are the absolute paths to the files and folders you want to clone.