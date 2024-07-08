DOCKERFILE=Dockerfile
CONTAINER=anna_homework:latest
export DOCKER_BUILDKIT=1

echo $DOCKERFILE $CONTAINER $NETWORK $PORTS

dbuild() {
    echo "Building ${CONTAINER}"
    docker build \
        --build-arg USER_ID=$(id -u) \
        --build-arg GROUP_ID=$(id -g) \
        -f $DOCKERFILE \
        -t $CONTAINER --target builder .
    echo "Done building ${CONTAINER}"
}

dbash() {
    echo "Starting ${CONTAINER}"
    docker run ${GPU_FLAGS} \
        --mount type=bind,source="/Users/sorenharner/PA5",target=/PA5/ \
        --rm ${NETWORK} ${PORTS} -it ${CONTAINER} bash
}
