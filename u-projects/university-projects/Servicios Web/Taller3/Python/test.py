from suds.client import Client
url = 'http://mottz.info/ictac2015/ExponerServiciosWebICTAC.php?wsdl'
client = Client(url)

ID = '0000000000'
tipoID = 'DL'

ID2 = '1144052533'
tipoID2 = 'ID'

result1 = client.service.ConsultarCertificadoUsuario(ID, tipoID)
result2 = client.service.ConsultarDescargaCertificado(ID, tipoID)
result3 = client.service.ConsultarInfoUsuario(ID2, tipoID2)

print result1
print result2
print result3
