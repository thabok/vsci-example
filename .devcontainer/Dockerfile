FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

USER root

RUN apt-get update \
    && apt-get install -y --no-install-recommends wget openjdk-21-jre \
    && cd /tmp \
    && wget https://github.com/Kitware/CMake/releases/download/v4.2.5/cmake-4.2.5-linux-x86_64.tar.gz \
    && tar --strip-components=1 -xzf cmake-4.2.5-linux-x86_64.tar.gz -C /usr/local \
    && rm -rf cmake-4.2.5-linux-x86_64* \
    && rm -rf /var/lib/apt/lists/*

USER vscode
