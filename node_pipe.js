var fs = require("fs");
var http = require('http');

// var data = 0;

const OUT_FILE = '/tmp/SCHOOLMAP_N2C';
const IN_FILE = '/tmp/SCHOOLMAP_C2N';

if (!fs.statSync(OUT_FILE).isFIFO()) {
  console.log("NO N2C FIFO!");
  process.exit(1);
}
if (!fs.statSync(IN_FILE).isFIFO()) {
  console.log("NO C2N FIFO!");
  process.exit(1);
}

var writeStream = fs.createWriteStream(OUT_FILE);
// writeStream.write('{"startpoint":1,"endpoint":10,"passpoint":[2,3,4,5,6],"by":"foot"}\n');
// setTimeout(()=>{
//   writeStream.write('{"startpoint":1,"endpoint":10,"passpoint":[2,3,4,5,6],"by":"foot"}\n');
// }, 1000);
// setInterval(()=>{
//   writeStream.write(data++ + '\n', 'UTF8');
// }, 1000);

var readStream = fs.createReadStream(IN_FILE);
readStream.setEncoding("UTF8");

http.createServer(function (req, resp) {
  console.log(req.method + ' ' + req.url);
  if (req.method == 'GET') {
    if (req.url == '/walk_map') {
      resp.end(fs.readFileSync("./data/walkMap.json"));
    } else if (req.url == '/car_map') {
      resp.end(fs.readFileSync("./data/carMap.json"));
    } else {
      resp.end('failed');
    }
  } else if (req.method == 'POST') {
    if (req.url == '/search_way') {
      var post_data = '';
      req.on('data', chunk=>post_data += chunk);
      req.on('end', ()=>{
        console.log(post_data);
        writeStream.write(post_data + '\n', 'UTF8');
        readStream.once('data', chunk=>{
          console.log(chunk);
          resp.end(chunk);
        });
      });
    }
  }
}).listen(8888);
