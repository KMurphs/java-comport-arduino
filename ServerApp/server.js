/* https://www.w3schools.com/nodejs/nodejs_http.asp */
/* https://blog.risingstack.com/your-first-node-js-http-server/ */

const express = require('express')
const mysql = require('mysql');
const bodyParser = require('body-parser');
const app = express()
const port = 3000


/////////////////////////////////////// SQL PART
const con = mysql.createConnection({
  host: "localhost",
  port: "3306",
  user: "fingerprintApp",
  password: "fingerprintApp",
  database: "attendancereg"
});
let isMYSLConnected = 0;
const initConnection = function(){
	con.connect(function(err) {
		if (err) throw err;
		isMYSLConnected = 1;
	});
}
///////////////////////////////////////
app.use((request, response, next) => {
  console.log(request.headers)
  next()
})

app.use((request, response, next) => {
  request.chance = Math.random()
  next()
})

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', (request, response) => {
  response.json({
    message: "Welcome to the FingerPrint App Server"
  })
})
app.get('/users', (request, response) => {
	if(isMYSLConnected == 0)initConnection();
	con.query("select * FROM attendancereg.students;", function (err, result, fields) {
		if (err) throw err;
		console.log(result);
		response.json(result)
	});
})
app.get('/users/:id', (request, response) => {
	if(isMYSLConnected == 0)initConnection();
	con.query(`SELECT * FROM attendancereg.students where UserID = '${request.params.id}';`, function (err, result, fields) {
		if (err) throw err;
		console.log(result[0]);
		response.json(result[0])
	});
})
app.post('/users', (request, response) => {
	//console.log(request.body)
	
	//var sql = "INSERT INTO customers (name, address) VALUES ('Company Inc', 'Highway 37')";
	let sql = "INSERT INTO `attendancereg`.`students` (`Name`, `Surname`, `IDNumber`, `StudentNumber`, `FingerPrint`, `isActive`, `Priviledge`) VALUES ?";
	//let values = [['Johannes', 'Ruberu', '123456', '2355848', 'sdfgsdfgdfghfghfgsdfgsdfgdfghdf', 1, 1]]
	let values = []
	let temp = []
	for(const item of [`Name`, `Surname`, `IDNumber`, `StudentNumber`, `FingerPrint`, `isActive`, `Priviledge`]){
		//console.log(request.body[item])
		temp.push(request.body[item])
	}
	values.push(temp)
 	con.query(sql, [values], function (err, result) {
		if (err) throw err;
		console.log(`${values.length} record inserted`);
		con.query(`SELECT * FROM attendancereg.students where IDNumber = ${request.body['IDNumber']};`, function (err, result, fields) {
			if (err) throw err;
			console.log(result[0]);
			response.json(result[0]);
		});
	});
})
app.post('/users/:id', (request, response) => {
	//console.log(request)
	//console.log(request.body)
	//console.log(request.params.id)
	
	
	if(!request.body['FingerPrint']){
		response.json({'message':'Inavlid FingerPrint'})
		return
		
	}

	
	var sql = `UPDATE attendancereg.students SET FingerPrint = '${request.body['FingerPrint']}' WHERE UserID = '${request.params.id}';`;
 	con.query(sql, function (err, result) {
		if (err) throw err;
		console.log(`1 record was updated`);
		con.query(`SELECT * FROM attendancereg.students where UserID = '${request.params.id}';`, function (err, result, fields) {
			if (err) throw err;
			console.log(result[0]);
			response.json(result[0])
		});
	});
})

app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)

  /* console.log(process.env) */
})

// C:\Users\JOHANNESR\Documents\Waveshare\branches\NodeJS-Server
// Start Server: npm start
// Stop Server: ctrl+C