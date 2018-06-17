I_want_to_learn=(Python JS zsh ROS)
echo "Print Array length"
array_len=${#I_want_to_learn[@]}
# Or you can define as ${#I_want_to_learn[*]}
echo $array_len
echo "Print second element's length"
ele2_len=${#I_want_to_learn[1]}
echo $ele2_len
