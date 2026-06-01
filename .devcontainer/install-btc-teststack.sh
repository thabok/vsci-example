set -euo pipefail

pw="ZejSa&Y3lV#0XxV3Vbb$"

# Download and extract BTC TestStack extensions
wget https://www.btc-embedded.com/downloads/software/btc.teststack-26.1.0-beta-linux.zip
echo "$pw" | unzip -P "$pw" btc.teststack-26.1.0-beta-linux.zip "installation/*.vsix" -d .
mv ./installation/*.vsix ./.devcontainer/btc-extensions/
rm -rf installation
rm btc.teststack-26.1.0-beta-linux.zip

export code="$(ls ~/.vscode-server*/bin/*/bin/code-server* | head -n 1)"
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-jre-26.1.0-beta.vsix"             --force
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-servicedaemon-26.1.0-beta.vsix"   --force
$code --install-extension ".devcontainer/btc-extensions/btc.teststack-26.1.0-beta.vsix"                 --force

echo "BTC extension installation complete."
