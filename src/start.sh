#!/bin/sh

dir=$1
proj_name=$2

if [ -f "$dir/$proj_name.raw" ] && [ -f  "$dir/$proj_name.iidx" ] && [ -f  "$dir/$proj_name.didx" ] ; then
    echo "ALL PREPARATION COMPLETE!"
    echo "start service now ?"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./serv $dir/$proj_name.raw $dir/$proj_name.iidx $dir/$proj_name.didx
    fi
fi
