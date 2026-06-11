set -euo pipefail

# Download and extract BTC TestStack extensions
build_id=".2089"
archive="btc.teststack-26.1.1-beta${build_id}-linux"
ext_dir="./.devcontainer/btc-extensions"

# if [ "$(ls .devcontainer/btc-extensions/*.vsix 2>/dev/null | wc -l)" -lt 3 ]; then
    # wget "https://www.btc-embedded.com/downloads/software/${archive}"
    # unzip -j "$archive" "installation/*.vsix" -d "$ext_dir"
    # rm -f "$archive"
# fi

export code="$(ls ~/.vscode-server*/bin/*/bin/code-server* | head -n 1)"
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-jre-26.1.1-beta${build_id}.vsix"             --force
# $code --install-extension ".devcontainer/btc-extensions/btc.teststack-servicedaemon-26.1.1-beta${build_id}.vsix"   --force
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-26.1.1-beta${build_id}.vsix"                 --force

echo "BTC extension installation complete."
