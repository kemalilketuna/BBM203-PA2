import zipfile

# List of files to be zipped
files = [
    'Block.h',
    'BlockFall.h',
    'BlockFall.cpp',
    'GameController.h',
    'GameController.cpp',
    'LeaderboardEntry.h',
    'LeaderboardEntry.cpp',
    'Leaderboard.h',
    'Leaderboard.cpp',
]

# Create a new zip file (or overwrite if it exists)
with zipfile.ZipFile("b2220356127.zip", "w") as z:
    for file in files:
        z.write(file)

print("Files zipped successfully into output.zip")