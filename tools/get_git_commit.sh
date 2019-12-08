#!/bin/bash

SOURCE_DIR=$1
GITCOMMIT=$(cd $SOURCE_DIR && git rev-parse HEAD)
echo "#define GITCOMMIT \"$GITCOMMIT\""  > git_commit.h
