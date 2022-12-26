# Affiche les nombres premiers jusqu'à $1

# On iter de 1 à i=$1
for ((i = 1; i <= $1; i++)); do
	premier=true
	# On cherche si i est divisible par un nombre entre 2 et i/2
	for ((j = 2; j <= $i / 2; j++)); do
		if [ $((i % j)) -eq 0 ]; then
			premier=false
		fi
	done
	# S'il ne l'est pas on le fait dire à la vache
	if [ $premier = true ]; then
		cowsay $i
		sleep 1
		clear
	fi
done
