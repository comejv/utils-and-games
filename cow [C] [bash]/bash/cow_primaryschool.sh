# Compte jusqu'à $1

if [[ $# -ne 1 ]]; then
 echo Il faut 1 argument.
 exit 1
fi

for ((i = 1; i <= $1; i++)); do
    clear
    cowsay $i
    sleep 1
done