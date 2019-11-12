const baseDir = process.cwd();

const request = require('https').request;

const API_HOSTNAME = 'api.weather.gov/';

const latitude = '37.762626', 
     longitude = '-122.435291';

const USER_AGENT =`"Nozilla/1.0 (console; pios x86_64 ${process.version}) AppleWebKit/537.36 (KHTML, like Gecko but not) xpi/70.1.1`;

const DISCOVER_ENDPOINT = `${API_ENDPOINT}/points/${latitude},${longitude}`;

const options = {
  hostname: API_HOSTNAME,
  port: 443,
  path: DISCOVER_ENDPOINT,
  method: 'GET', 
  headers: {
      'User-Agent': USER_AGENT        
  }
};

const req = https.request(options, (res) => {
  console.log('statusCode:', res.statusCode);
  console.log('headers:', res.headers);

  res.on('data', (d) => {
    process.stdout.write(d);
  });
});

req.on('error', (e) => {
  console.error(e);
});
req.end();


