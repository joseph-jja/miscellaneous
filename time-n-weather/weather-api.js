const baseDir = process.cwd();

const request = require('https').request, 
    fs = require('fs'),
    os = require('os');

const API_HOSTNAME = 'api.weather.gov';

const latitude = '37.7626',
    longitude = '-122.4352';

const RELOAD = 1000 * 60 * 60;

const USER_AGENT = `"Nozilla/1.0 (console; pios x86_64 ${process.version}) AppleWebKit/537.36 (KHTML, like Gecko but not) xpi/70.1.1`;

const DISCOVER_ENDPOINT = `/points/${latitude},${longitude}`;

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

                resolve(results.properties);
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
    //console.log(props);

    options.path = props.forecastHourly.split(API_HOSTNAME)[1];
    const forecast = await makeRequest(options);

    let details = `Hourly: ${os.EOL}`; 
    forecast.periods.filter((period, index) => {
        // 8 hours only 
        return (index < 8); 
    }).forEach(period => {
        const startTime = period.startTime.split('T')[1].split('-')[0],
            endTime = period.endTime.split('T')[1].split('-')[0];
        details += `  (${startTime}-${endTime}): ${period.temperature}${period.temperatureUnit} / ${period.windSpeed} ${period.windDirection} ${os.EOL}`; 
    });
    
    //console.log(details);
    fs.writeFile('/tmp/hourly.txt', details, (errx) => {
        // TODO handle error?
    });
}

start();
setInterval(start, RELOAD);


