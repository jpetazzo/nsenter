#!/bin/sh

if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Usage: docker-run CONTAINER SCRIPT [ARG]..."
  echo ""
  echo "Enters the Docker CONTAINER and executes the specified shell script"
else
  CONTAINERID=$(docker inspect --format "{{.Id}}" "$1")
  CONTAINERFS=/var/lib/docker/aufs/mnt/$CONTAINERID/
  if [ -z $CONTAINERID ]; then
    echo "Container not found"
    exit 1
  fi

  cp $2 $CONTAINERFS
  chmod +x $CONTAINERFS/$2
  docker-enter $1 $2
  rm $CONTAINERFS/$2
fi
