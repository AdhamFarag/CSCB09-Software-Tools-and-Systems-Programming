for f in *; do
  if [ -f "$f" ]; then
    if echo $f | grep [A-Z] >/dev/null; then
      echo "*$f"
    else
      echo $f
  fi
  fi
done
