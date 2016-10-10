require 'savon'

# create a client for the service
client = Savon.client(wsdl: 'http://mottz.info/ictac2015/ExponerServiciosWebICTAC.php?wsdl')

client.operations
# => [:find_user, :list_users]

# call the 'findUser' operation
response = client.call(:consultar_info_usuario, message: { id: "1144052533", tipoID: "ID" })

puts response.doc
# => { find_user_response: { id: 42, name: 'Hoff' } }