# Cowsay prononce les chiffres de 1 à 10
for ((i = 1; i <= 10; i++)); do
    clear
    cowsay $i
    sleep 1
done
cowthink -T U -e ^^ I did great !
