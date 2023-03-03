// const express = require('express');
// const mqtt = require('mqtt');
// const mongoClient = require('mongodb').MongoClient;
// const uri = "mongodb+srv://doadmin:f623g1cDYM05Wp79@db-mongodb-nyc3-29938-65da0883.mongo.ondigitalocean.com/admin?tls=true&authSource=admin&replicaSet=db-mongodb-nyc3-29938"
// const client = mqtt.connect('mqtt://192.168.1.19:1883');

// const app = express()
// app.use(express.json())

// client.on('connect', () => {
//     client.subscribe('sensor/humi');
//     console.log('MQTT client connected');
// });

// client.on('message', (topic, message) => {
//     console.log(`Received message: ${message.toString()}`);

//     mongoClient.connect(uri, (err, db) => {

//         if (err) {
//             console.log("Error while connecting mongo client")
//         } else {

//             const myDb = db.db('FarmSensor')
//             const collection = myDb.collection('sensor/humi')

//             console.log("...............")
//             console.log("connected to MongoDB")

//             const data = { value: message.toString() };
//             collection.insertOne(data, (err, res) => {
//                 console.log("Data inserted");
//                 db.close();
//             });
//         }
//     })
// })
// app.get('/sensor/humi', (req, res) => {
//     mongoClient.connect(uri, (err, db) => {
//         if (err) {
//             res.send("Error while connecting to MongoDB");
//         } else {
//             const myDb = db.db('FarmSensor')
//             const collection = myDb.collection('sensor/humi')

//             collection.find().toArray((err, data) => {
//                 if (err) {
//                     res.send("Error while retrieving data");
//                 } else {
//                     res.send(data);
//                 }
//                 db.close();
//             });
//         }
//     });
// });



// app.listen(3000, () => {
//     console.log("listen port 3000")
// })

//------------------------------------------

const express = require('express');
const mqtt = require('mqtt');
const mongoClient = require('mongodb').MongoClient;
const uri = "mongodb+srv://doadmin:5fIX0x6719s3KMT8@mongodb-farmstay-377e851f.mongo.ondigitalocean.com/admin?authSource=admin&tls=true"
// const options = {
//     username: 'farmstay',
//     password: 'farmstay'
// };
// const client = mqtt.connect('mqtt://192.168.1.37:1883', options);


const app = express()
app.use(express.json())

// const topics = ['sensor/moisture', 'sensor/humi', 'sensor/temp', 'sensor/fire', 'sensor/waterlevel', 'sensor/rfid'];

// client.on('connect', () => {
//     topics.forEach(topic => {
//         client.subscribe(topic);
//         console.log(`Subscribed to topic: ${topic}`);
//     });
//     console.log('MQTT client connected');
// });

// client.on('message', (topic, message) => {
//     console.log(`Received message from topic ${topic}: ${message.toString()}`);

//     mongoClient.connect(uri, (err, db) => {

//         if (err) {
//             console.log("Error while connecting mongo client")
//         } else {

//             const myDb = db.db('FarmSensor')
//             const collection = myDb.collection(topic)

//             console.log("...............")
//             console.log("connected to MongoDB")

//             const data = { value: message.toString() };
//             collection.insertOne(data, (err, res) => {
//                 console.log("Data inserted");
//                 db.close();
//             });
//         }
//     })
// });
app.get('/sensor/rfid', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/rfid')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
app.get('/sensor/humi', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/humi')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
app.get('/sensor/temp', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/temp')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
app.get('/sensor/moisture', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/moisture')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
app.get('/sensor/fire', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/fire')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
app.get('/sensor/waterlevel', (req, res) => {
    mongoClient.connect(uri, (err, db) => {
        if (err) {
            res.send("Error while connecting to MongoDB");
        } else {
            const myDb = db.db('FarmSensor')
            const collection = myDb.collection('sensor/waterlevel')

            collection.find().toArray((err, data) => {
                if (err) {
                    res.send("Error while retrieving data");
                } else {
                    res.send(data);
                }
                db.close();
            });
        }
    });
});
// const router = express.Router();

// router.get('/:channel', (req, res) => {
//     const channel = req.params.channel;
//     const state = req.query.state;

//     if (channel < 1 || channel > 4) {
//         res.status(404).send({ message: 'Invalid channel number' });
//         return;
//     }

//     if (state === '1') {
//         client.publish(`relay${channel}`, '1');
//         res.send({ message: `Turn on relay ${channel}` });
//     } else if (state === '0') {
//         client.publish(`relay${channel}`, '0');
//         res.send({ message: `Turn off relay ${channel}` });
//     } else {
//         res.status(400).send({ message: 'Invalid state value' });
//     }
// });

// app.use('/api', router);
app.listen(3000, () => {
    console.log("listen port 3000")
})

//------------------------------------------------------------------

// const express = require('express');
// const bodyParser = require('body-parser');
// const mqtt = require('mqtt');

// const app = express();
// const client = mqtt.connect('mqtt://192.168.1.87', {
//   username: 'farmstay',
//   password: 'farmstay'
// });

// app.use(bodyParser.urlencoded({ extended: true }));
// app.use(bodyParser.json());

// const router = express.Router();

// router.get('/:channel', (req, res) => {
//   const channel = req.params.channel;
//   const state = req.query.state;

//   if (channel < 1 || channel > 4) {
//     res.status(404).send({ message: 'Invalid channel number' });
//     return;
//   }

//   if (state === '1') {
//     client.publish(`relay${channel}`, '1');
//     res.send({ message: `Turn on relay ${channel}` });
//   } else if (state === '0') {
//     client.publish(`relay${channel}`, '0');
//     res.send({ message: `Turn off relay ${channel}` });
//   } else {
//     res.status(400).send({ message: 'Invalid state value' });
//   }
// });

// app.use('/api', router);

// app.listen(3000, () => {
//   console.log('Server started on port 3000');
// });

