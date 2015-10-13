echo "converting image sequences to video"
cd bin/data/media
ffmpeg -f image2 -i "right/frame_%04d.png" right.mpg
ffmpeg -f image2 -i "left/frame_%04d.png" left.mpg