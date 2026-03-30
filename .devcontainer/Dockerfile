FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

USER root

RUN apt-get update \
    && apt-get install -y --no-install-recommends wget \
    && cd /tmp \
    && wget https://github.com/Kitware/CMake/releases/download/v3.31.0/cmake-3.31.0-linux-x86_64.tar.gz \
    && tar --strip-components=1 -xzf cmake-3.31.0-linux-x86_64.tar.gz -C /usr/local \
    && rm -rf cmake-3.31.0-linux-x86_64* \
    && rm -rf /var/lib/apt/lists/*

USER vscode
