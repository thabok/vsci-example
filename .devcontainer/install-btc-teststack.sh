set -euo pipefail

#https://www.btc-embedded.com/downloads/software/btc.teststack-vscode.26.1.6-beta-linux.zip

# Download and extract BTC TestStack extensions
btc_version="26.1.6-beta"
archive="btc.teststack-vscode.${btc_version}-linux.zip"
ext_dir="./.devcontainer/btc-extensions"

if [ "$(ls .devcontainer/btc-extensions/*.vsix 2>/dev/null | wc -l)" -lt 1 ]; then
    wget "https://www.btc-embedded.com/downloads/software/${archive}"
    unzip -j "$archive" "installation/*.vsix" -d "$ext_dir"
    rm -f "$archive"
fi

export code="$(ls ~/.vscode-server*/bin/*/bin/code-server* | head -n 1)"
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-${btc_version}.vsix"                 --force

echo "BTC extension installation complete."
