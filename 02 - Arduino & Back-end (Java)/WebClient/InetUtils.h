
/*change interface name*/
void setupInterfaceName(){ //https://stackoverflow.com/questions/40405909/arduino-intel-galileo-gen-2-ethernet-ip-not-set
  system("ifconfig enp0s20f6 down ");
  system("ip link set enp0s20f6 name eth0");
  system("ifconfig eth0 up");
}

/*IPAddress to String*/
String IPAddress2String(const IPAddress ipAddress){
  return String(ipAddress[0])+String(".")+String(ipAddress[1])+String(".")+String(ipAddress[2])+String(".")+String(ipAddress[3]);
}

/*make http request, TODO: method -> enum & headers array*/
void httpRequest(IPAddress server,int port,String method,String uri,char *payload){
    EthernetClient client;
    if (client.connect(server, port)) {
      client.println(method+" "+uri+" HTTP/1.1");
      client.println("Host: "+IPAddress2String(server));
      client.println("User-Agent: Galileo");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(strlen(payload));// number of bytes in the payload
      client.println();// important need an empty line here 
      client.println(payload);// the payload

      while(client.connected()){//TODO read body
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }else{
          client.stop();
        }
      }
  }else{
    Serial.println("can not connect to: "+IPAddress2String(server)+":"+port);
  }
}
