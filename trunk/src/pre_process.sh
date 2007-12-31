#!/bin/sh
#code by Joyan

dir=$1
proj_name=$2

export LC_ALL=zh_CN.gb2312

if [ ! $proj_name ] ; then
    echo "USAGE: $0 dir_name proj_name"
    echo ""
    exit
fi

if [ ! -d $dir ] ; then
    echo "[ERROR]:Directory $dir doesn't exist!"
    echo ""
    exit
fi

echo "Prepare to crawl..."
if [ -f "$dir/$proj_name.raw" ] ; then
    echo "[WARNING]:$dir/$proj_name.raw exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./crawl $dir
    fi
else
    ./crawl $dir
fi

echo "Prepare to docid2offset..."
if [ -f "$dir/$proj_name.didx" ] ; then
    echo "[WARNING]:$dir/$proj_name.didx exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./docoff $dir/$proj_name.raw
    fi
else
    ./docoff $dir/$proj_name.raw
fi

echo "Prepare to seg word..."
if [ -f "$dir/$proj_name.raw.seg" ] ; then
    echo "[WARNING]:$dir/$proj_name.raw.seg exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./rawseg $dir/$proj_name.raw $dir/$proj_name.didx
    fi
else
    ./rawseg $dir/$proj_name.raw $dir/$proj_name.didx
fi

echo "Prepare to create piidx file..."
if [ -f "$dir/$proj_name.piidx" ] ; then
    echo "[WARNING]:$dir/$proj_name.piidx exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./preinvert $dir/$proj_name.raw.seg
    fi
else
    ./preinvert $dir/$proj_name.raw.seg
fi

echo "Prepare to sort piidx file..."
if [ -f "$dir/$proj_name.piidx.sort" ] ; then
    echo "[WARNING]:$dir/$proj_name.piidx.sort exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        sort $dir/$proj_name.piidx >  $dir/$proj_name.piidx.sort
    fi
else
    sort $dir/$proj_name.piidx >  $dir/$proj_name.piidx.sort
fi

echo "Prepare to create iidx file.."
if [ -f "$dir/$proj_name.iidx" ] ; then
    echo "[WARNING]:$dir/$proj_name.iidx exists! Overwrite ?[y/n]"
    read input
    if [[ $input == [Yy]* ]] ; then
        ./invert $dir/$proj_name.piidx.sort
    fi
else
    ./invert $dir/$proj_name.piidx.sort
fi

./start.sh $dir $proj_name
