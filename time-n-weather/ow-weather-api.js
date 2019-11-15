const baseDir = process.cwd();

const request = require('https').request, 
    fs = require('fs'), 
    {
        promisify
    } = require('util');

const readFile = promisify(fs.readFile);

const API_HOSTNAME = 'api.openweathermap.org';

const latitude = '37.7626',
    longitude = '-122.4352';

const USER_AGENT = `"Nozilla/1.0 (console; pios x86_64 ${process.version}) AppleWebKit/537.36 (KHTML, like Gecko but not) xpi/70.1.1`;

const DISCOVER_ENDPOINT = `/data/2.5/weather?lat=${latitude}&lon=${longitude}`;

const options = {
    hostname: API_HOSTNAME,
    port: 443,
    path: DISCOVER_ENDPOINT,
    method: 'GET',
    headers: {
        'User-Agent': USER_AGENT
    }
};

async function makeRequest(options) {

    const keyFile = await readFile(`${baseDir}/config.json`);
    key = JSON.parse(keyFile.toString()).key;

    options.path += `&APPID=${key}`;

    return new Promise((resolve, reject) => {

        const req = request(options, (res) => {
            //  console.log('statusCode:', res.statusCode);
            //  console.log('headers:', res.headers);

            const chunks = [];
            res.on('data', (d) => {
                chunks.push(d);
            });

            res.on('error', (e) => {
                reject(e);
            });
            res.on('end', () => {
                const results = JSON.parse(Buffer.concat(chunks));

                resolve(results);
            });
        });

        req.on('error', (e) => {
            reject(e);
        });
        req.end();
    });
}

async function start() {

    const props = await makeRequest(options);

    console.log(props);
}

start();
