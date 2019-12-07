const baseDir = process.cwd();

const request = require('https').request, 
    os = require('os'), 
    fs = require('fs'), 
    {
        promisify
    } = require('util');

const readFile = promisify(fs.readFile);

const API_HOSTNAME = 'api.openweathermap.org';

const latitude = '37.7626',
    longitude = '-122.4352';

const RELOAD = 1000 * 60 * 60; 

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
                console.error(e);
                reject(e);
            });
            res.on('end', () => {
                const results = JSON.parse(Buffer.concat(chunks));

                resolve(results);
            });
        });

        req.on('error', (e) => {
            console.error(e);
            reject(e);
        });
        req.end();
    });
}

function toFahrenheit(kelvin) {
    const raw = (9/5 * kelvin - 459.67);
    return `${(Math.round(raw * 10) / 10)}F`;
}

async function start() {

    //const results = require('/tmp/full.js');
    const results = await makeRequest(options);
    const main = results.main;

    const temp = `Current: ${toFahrenheit(main.temp)}`;
    const tempMin = toFahrenheit(main.temp_min);
    const tempMax = toFahrenheit(main.temp_max);

    const tempRange = `Low: ${tempMin} - High: ${tempMax}`;
    const humidity = `Humidity: ${main.humidity}%`;
    const cloudy =  `Clouds: ${results.clouds['all'] || 0}%`;
    const rain = `Rain: ${results.rain && results.rain['1h'] || 0} / ${results.rain && results.rain['3h'] || 0}`;

    const data = `${temp}${os.EOL}${tempRange}${os.EOL}${humidity}${os.EOL}${cloudy}${os.EOL}${rain}${os.EOL}`;

    fs.writeFile('/tmp/details.txt', data, () => {}) ;
    fs.writeFile('/tmp/full.js', `module.exports = ${JSON.stringify(results)};`, () => {}) ;

}

start();
setInterval(start, RELOAD);




