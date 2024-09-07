# Dockerfile

# Utilise une image de base Ubuntu
FROM ubuntu:latest

# Met à jour les paquets et installe les bibliothèques nécessaires
RUN apt-get update && apt-get install -y \
    clang \
    lldb \
    build-essential \
    sudo \
    valgrind \
    bc \
    libbsd-dev \
    libx11-6 \
    x11-apps && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

# Définir le point d'entrée pour exécuter un programme graphique X11
CMD ["/bin/bash"]

