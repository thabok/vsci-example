#!/bin/bash

# currently not used, waiting for linux support of btc vsci

set -euo pipefail

# # Array of extension URLs to download and install
# EXTENSIONS=(
#   "http://foo.bar/btc-extension1.vsix"
#   "http://foo.bar/btc-extension2.vsix"
#   "http://foo.bar/btc-extension3.vsix"
# )

# # Temporary directory for downloads
# TEMP_DIR=$(mktemp -d)
# trap "rm -rf $TEMP_DIR" EXIT

# echo "Installing BTC Extensions..."

# # Loop through and install each extension
# for ext_url in "${EXTENSIONS[@]}"; do
#   ext_name=$(basename "$ext_url")
#   ext_path="$TEMP_DIR/$ext_name"
  
#   echo "Downloading $ext_name from $ext_url..."
  
#   if curl -fL "$ext_url" -o "$ext_path"; then
#     echo "Installing $ext_name..."
#     if code-server --install-extension "$ext_path" 2>/dev/null || \
#        code --install-extension "$ext_path" 2>/dev/null; then
#       echo "✓ Successfully installed $ext_name"
#     else
#       echo "✗ Failed to install $ext_name"
#     fi
#   else
#     echo "✗ Failed to download $ext_name from $ext_url"
#   fi
# done

# workaround because code executable is not in PATH when running this script, we need to find it first
export code="$(ls ~/.vscode-server*/bin/*/bin/code-server* | head -n 1)"
$code --install-extension ".devcontainer/btc-extensions/jre.vsix"      --force
$code --install-extension ".devcontainer/btc-extensions/backend.vsix"  --force
$code --install-extension ".devcontainer/btc-extensions/frontend.vsix" --force

echo "BTC extension installation complete."
