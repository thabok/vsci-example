set -euo pipefail

# Download and extract BTC TestStack extensions
pw="ZejSa&Y3lV#0XxV3Vbb$"
#archive="btc.teststack-26.1.0-beta-linux.zip"
archive="btc.teststack-26.1.0-beta.1920-linux.zip"
ext_dir="./.devcontainer/btc-extensions"
# wget "https://www.btc-embedded.com/downloads/software/${archive}"
unzip -j -P "$pw" "$archive" "installation/*.vsix" -d "$ext_dir"
rm -f "$archive"

if command -v code >/dev/null 2>&1; then
	code_bin="code"
else
	code_bin="$(find "$HOME" -type f -path '*/.vscode-server*/bin/*/bin/code-server*' -print -quit)"
fi

if [[ -z "$code_bin" ]]; then
	echo "No VS Code CLI found (expected 'code' or code-server)." >&2
	exit 1
fi

"$code_bin" --install-extension ".devcontainer/btc-extensions/btc.teststack-jre-26.1.0-beta.vsix"             --force
"$code_bin" --install-extension ".devcontainer/btc-extensions/btc.teststack-servicedaemon-26.1.0-beta.vsix"   --force
"$code_bin" --install-extension ".devcontainer/btc-extensions/btc.teststack-26.1.0-beta.vsix"                 --force

echo "BTC extension installation complete."
