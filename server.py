import socket,thread

host = '192.168.43.173'
port = 1279

def writeClient(clientsocket,addr):
    print("A new thread has been created for the client: "+str(clientsocket)+","+str(addr))
    data = clientsocket.recv(2048)
    data=data.replace("\r","")
    print("Data Received:\n"+data)
    data = data.split("\n")
    filename = data[0]
    filename = filename.replace("\n",'')
    filename+=".txt"
    f = open(filename,"w")
    print("A new file with the name: "+filename+" has been created")
    clientsocket.send("OK")
    try:
        for i in data[1:]:
            s = i.replace("\r","")
            s+="\n"
            f.write(s)
        while True:
            data = clientsocket.recv(2048)
            clientsocket.send("OK")
    except Exception as e:
        f.close()
        print("File has veen closed due to this error("+str(e)+")")


if __name__=="__main__":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host,port))
    print(s.getsockname())
    s.listen(10)

    print("Listening to connections...")

    try:
        while True:
            clientsocket,addr = s.accept()
            thread.start_new_thread(writeClient, (clientsocket, addr))
    except Exception as e:
        s.close()
        print("Server Closed due to this error("+str(e)+")")