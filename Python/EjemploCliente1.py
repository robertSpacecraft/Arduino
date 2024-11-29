import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.100.24",2019))
print("Se conecto al servidor!")
s.close()
print("Fin del programa")
