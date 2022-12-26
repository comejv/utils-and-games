# Affiche la suite fibonacci jusqu'à $1

a=0
b=1

while [[ $a -lt $1 ]]; do
    clear
    cowsay "$a "
    sleep 1
    fn=$((a + b))
    a=$b
    b=$fn
done
