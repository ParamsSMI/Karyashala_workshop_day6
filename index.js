const express = require('express')
const app = express()
var Routes = require('./allRoutes');
var path = require('path');
const { request } = require('http');
const { response } = require('express');
const port = 3000

app.use('/home',Routes);

app.listen(port, () => {
  console.log(`App running on "http://localhost:${port}/home"`)
})