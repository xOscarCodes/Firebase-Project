const firebaseConfig = {
    apiKey: "AIzaSyDkiotMs4F4VV0PpD82Z9T_0CJcer1sTQs",
    authDomain: "webled-af64d.firebaseapp.com",
    databaseURL: "https://webled-af64d-default-rtdb.firebaseio.com",
    projectId: "webled-af64d",
    storageBucket: "webled-af64d.appspot.com",
    messagingSenderId: "76157285529",
    appId: "1:76157285529:web:b008c01296c5ea2309f408",
    measurementId: "G-8BV4E4CX39"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

function ledRED() {
    firebase.database().ref("status/").set("RED")
}

function ledYELLOW() {
    firebase.database().ref("status/").set("YELLOW")
}

function ledGREEN() {
    firebase.database().ref("status/").set("GREEN")
}

function ledOFF() {
    firebase.database().ref("status/").set("OFF")
}

