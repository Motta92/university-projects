require 'savon'

# create a client for the service
client = Savon.client(wsdl: 'http://mottz.info/ictac2015/ExponerServiciosWebICTAC.php?wsdl')

client.operations

# Consultar Certificado Usuario
response = client.call(:consultar_certificado_usuario, message: { id: "1144052533", tipoID: "ID" })
puts response.doc

# Consultar Descarga Certificado
response = client.call(:consultar_descarga_certificado, message: { id: "1144052533", tipoID: "ID" })
puts response.doc

# Consultar Informacion Usuario
response = client.call(:consultar_info_usuario, message: { id: "1144052533", tipoID: "ID" })
puts response.doc