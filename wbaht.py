import os
import sys
import platform

def solve(command, file_d):
    print(file_d, "start converting html..")
    val = os.system(command)
    generateLogFile(file_d, val)

def folderTraversal(filepath, tab, template):
    files = os.listdir(filepath)
    for file in files:
        file_d = os.path.join(filepath, file)
        if os.path.isdir(file_d):
            folderTraversal(file_d, tab, template)
        else:
            if file_d.lower().endswith('html'):
                return 
            if file_d.lower().endswith('java'):
                languange = 'JAVA'
            elif file_d.lower().endswith('cpp'):
                languange = 'CPP'
            else:
                languange = 'C'
            s = "baht -l " + languange + " -t " + tab + " -p " + template + " -f " + file_d
            solve(s, file_d)

def generateIndexHtml(step, filepath):
    openFile(step, filepath)
    files = os.listdir(filepath)
    for file in files:
        file_d = os.path.join(filepath, file)
        if os.path.isdir(file_d):
            generateIndexHtml(step + 1, file_d)

def openFile(step, filename):
    if (platform.system()=='Windows'):
        write_file_name = filename + '\\index.html'
    else :
        write_file_name = filename + '/index.html'
        
    fo = open(write_file_name, 'w')
    s =  '<html>\n'
    s += '   <head>\n'
    s += '       <title>Index of /archlinuxarm/</title>\n'
    s += '   </head>\n'
    s += '   <body bgcolor="white">\n'
    if step != 1:
        s += '       <h1>Index of /archlinuxarm/</h1><hr>\n'
        s += '            <pre><a href="../index.html">../</a>\n'
    else:
        s += '       <h1>Index of /archlinuxarm/</h1><hr><pre>\n'
    
    for file in os.listdir(filename):
        file_d = os.path.join(filename, file)
        if os.path.isdir(file_d):
            s += '<a href="' + file + '/index.html">' + file + '/</a>\n'

    for file in os.listdir(filename):
        file_d = os.path.join(filename, file) 
        if file_d.lower().endswith('html') and file.lower() != 'index.html':
            p = file[:-5]
            s += '<a href="' + file + '">' + p + '</a>\n'

    s += '      </pre><hr>\n'
    s += '  </body>\n'
    s += '</html>\n'
    fo.write(s)
    fo.close() 

def judgeTokenIsExist(tokenpath):
    # If the file which is located in tokenpath
    # has not existed, it will throw some exception.
    foo = open(tokenpath, 'r')
    foo.close()

def generateLogFile(file_d, status):
    foo = open("index.log", "a")
    if status == 0:
        s = file_d + " has ended with converting, Nice!"
        print(s)
        foo.write(s + "\n")
    else:
        s = file_d + " has occurred an error..........."
        print(s)
        foo.write(s + "\n")


# for test
    # folderTraversal("C:\\Users\\tortu\\Desktop\\2\\test")
    # solve("cd test")
    # openFile('C:\\Users\\tortu\\Desktop\\2\\test')

# folderTraversal("C:\\Users\\tortu\\Desktop\\2\\test")
# generateIndexHtml("C:\\Users\\tortu\\Desktop\\2\\test")
def main():
    '''
    print(len(sys.argv))
    for i in range(len(sys.argv)):
        print(sys.argv[i])
    '''
    print("**************************************************************")
    print("*Welcome to use the gadget that can let code convert to html!*")
    print("**************************************************************")
    '''
    You must give the program three parameters, 
          -t 
            show how many spaces before indentation
          -p
            where the template file is (with html suffix)
          -d
            which directory to be converted
    '''
    if (len(sys.argv) != 7):
        raise "The argv array's length must be 7.";
    if (sys.argv[1] != '-t' or sys.argv[3] != '-p' or
        sys.argv[5] != '-d'):
        raise "Error parameter list."

    judgeTokenIsExist(sys.argv[4])
    folderTraversal(sys.argv[6], sys.argv[2], sys.argv[4])
    generateIndexHtml(1, sys.argv[6])

if __name__ == "__main__":
    main()

