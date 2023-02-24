rurl="$1" && shift 1

dirname=$(basename ${rurl%.git})

if [-d "$dirname"]; then
  echo "$dirname existe déjà, ajout des fichiers demandés..."
  cd $dirname
else
  git clone --filter=blob:none --no-checkout "$rurl"
  cd $dirname

  echo "Initializing sparse-checkout..."
  git sparse-checkout init --cone

  git checkout HEAD
fi


echo "Adding selected dirs..."
if [ $# -gt 0 ]; then
  git sparse-checkout set "$@"
else
  echo "No folder given. Nothing to checkout."
fi

echo "Done, sparse-cloned $dirname."