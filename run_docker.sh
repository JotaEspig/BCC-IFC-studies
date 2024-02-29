#!/bin/bash
export PATH="/home/aluno/bin:$PATH"

pwd=$(pwd)
container_id=


install() {
    echo "Installing rootless docker"
    cd /tmp
    git clone https://github.com/docker/docker-install
    cd docker-install
    ./rootless-install.sh
    cd $pwd
}

run() {
    image=$1
    if [ ! -f ".container_id" ]; then
        container_id=$(docker run -it --rm --detach $image)
        echo $container_id > .container_id
    fi

    container_id=$(cat .container_id)
    docker start $container_id
    docker exec -it $container_id /bin/bash
}

main() {
    command -v docker &> /dev/null
    notfound=$?
    if [ $notfound -eq "1" ] ; then
        echo "Docker not found... Installing"
        install
    fi

    echo "running Docker"
    run $1
}

main $1
