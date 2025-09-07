# When atmost a single pair of braces is present
def getAllWords(query: str):
    if "{" not in query or "}" not in query:
        return query
    splits = query.split('{')
    prefix = splits[0]
    listOfWords = splits[1].split('}')[0]
    suffix = query.split('}').pop()
    words = listOfWords.split(',')
    if len(words) < 2:
        return query
        
    combinations = []
    for word in words:
        combinations.append(prefix + word + suffix)
    return combinations

# When multiple pairs of braces can be present
def getAllWords2(query: str):
    if "{" not in query or "}" not in query:
        return query
    segments = []
    wordsStr = []
    splits = query.split("{")
    for split in splits:
        temp = split.split('}')
        if len(temp) > 1:
            wordsStr.append(temp[0])
        segments.append(temp.pop())
    print(segments)
    words = []
    for word in wordsStr:
        words.append(word.split(','))
    print(words)
    combinations = []
    # for word in words:
    #     combinations.append(prefix + word + suffix)
    return combinations

combinations = getAllWords("over{crowd,eager,bold,fond}ness")

for word in combinations:
    print(word)
    
combinations2 = getAllWords("over{bold}ness")

if(type(combinations2)==str):
    print(combinations2)
else:
    for word in combinations2:
        print(word)

    
combinations2 = getAllWords2("over{bold,eager}nesshello{nice,good,bad}world")

if(type(combinations2)==str):
    print(combinations2)
else:
    for word in combinations2:
        print(word)