# Pas fini, trouver qqc d'intéressant à faire

while read l; do
    if [[ $l == touch* ]]; then
         $l
    fi
done <<<$(cat ~/.bash_history)
