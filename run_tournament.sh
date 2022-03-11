#!/usr/bin/env bash

make re -s ANIMATION_USLEEP=30
make bot -s

function play_matches() {
  ./cluster "bots/$1" "bots/$2" "$3"
  sleep 1
  ./cluster "bots/$2" "bots/$1" "$3"
  sleep 1
}

function tournament() {
  size="--size=$1"

  play_matches Jorien Peer "$size"

  play_matches Jorien Oscar "$size"

  play_matches Tiemen Jorien "$size"

  play_matches Tiemen Peer "$size"

  play_matches Tiemen Oscar "$size"

  play_matches Peer Oscar "$size"
}

tournament 5
tournament 7
tournament 4
#tournament 10
#tournament 15
