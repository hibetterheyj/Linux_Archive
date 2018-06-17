#! /bin/bash
echo "- Before Del, try echo"
myURL="hibetterheyj.github.io"
echo $myURL
echo "-----------------------"
unset myURL
echo "- After Del, try echo"
echo $myURL
