const { request, response } = require('express');
var express = require('express');
const { route } = require('express/lib/application');
var router = express.Router();
const bodyParser = require('body-parser')

router.use(bodyParser.json())
router.use(
  bodyParser.urlencoded({
    extended: true,
  })
)
  
router.post('/',(request,response)=>{
       console.log(request.body);  
});

module.exports = router;