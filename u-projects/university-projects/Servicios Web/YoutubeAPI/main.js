// Your use of the YouTube API must comply with the Terms of Service:
// https://developers.google.com/youtube/terms
var nextPage;
var prevPage;
var lquery;
// Helper function to display JavaScript value on HTML page.
function showResponse(response) {
    //var responseString = JSON.stringify(response, '', 2);
    //document.getElementById('test').innerHTML += responseString;
    
    var videos = $('.row');

    $('.row').empty();
    var html = '';
    for(var i = 1; i <= 10; i++){
        var thumbnail = response.items[i].snippet.thumbnails.medium.url;
        var caption = response.items[i].snippet.title;
        var videoID = response.items[i].id.videoId;
        //var video = "javascript:playVideo('thumbnail',"+ videoID +")";
        html += '<div class="col-md-2" id="one">';
        html += '<div class="thumbnail">';
        html += '<a href="#" class="thumbnail">';
        html += '<iframe width="384" height="216" src="https://www.youtube.com/embed/'+ videoID +'" frameborder="0" allowfullscreen="">';
        html += '</iframe>';
        //html += ' <img src="' + thumbnail +'"/>';
        html += '</a>';
        html += '<div class="caption"><h5>'+ caption +'</h5>';
        html += '</div>';
        html += '</div>';
        html += '</div>';
    }

    videos.append(html);
    window.scrollTo(0,0);
}

// Called automatically when JavaScript client library is loaded.
function onClientLoad() {
    gapi.client.load('youtube', 'v3', onYouTubeApiLoad);
}

// Called automatically when YouTube API interface is loaded (see line 9).
function onYouTubeApiLoad() {
    // This API key is intended for use only in this lesson.
    // See http://goo.gl/PdPA1 to get a key for your own applications.
    gapi.client.setApiKey('AIzaSyBergCrhPFrrWWxM5Xl2xDJnVeCxX-y8To');
    
    search(getSearch());
}

function search(query) {
    // Use the JavaScript client library to create a search.list() API call.
    var request = gapi.client.youtube.search.list({
        part: 'snippet',
        maxResults: 11,
        q: query
    });
    
    // Send the request to the API server,
    // and invoke onSearchRepsonse() with the response.
    request.execute(onSearchResponse);
}

function nextVideo(){
    var query = document.getElementById('buscar').value;
    console.log(query);
    var request = gapi.client.youtube.search.list({
        part: 'snippet',
        maxResults: 11,
        pageToken: nextPage,
        q: query
    });
    request.execute(onSearchResponse);
}

function prevVideo(){
    var query = document.getElementById('buscar').value;
    console.log(query);
    var request = gapi.client.youtube.search.list({
        part: 'snippet',
        maxResults: 11,
        pageToken: prevPage,
        q: query
    });
    request.execute(onSearchResponse);
}

function searchForArtist(){}

function searchForLicense(){
    var query = document.getElementById('buscar').value;
    console.log(query);
    var request = gapi.client.youtube.search.list({
        part: 'status',
        maxResults: 11,
        q: query
    });
    request.execute(onSearchResponse);
}

function searchForMaxResults(){}

// Called automatically with the response of the YouTube API request.
function onSearchResponse(response) {
    showResponse(response);
    nextPage = response.nextPageToken;
    prevPage = response.prevPageToken;
}

function getSearch(){
    var query = document.getElementById('buscar').value;
    lquery = query;
    console.log(query);
    search(lquery);
}



/*

USEFUL LINKS!

http://www.smashingmagazine.com/2012/02/09/beginners-guide-jquery-based-json-api-clients/

http://www.codecademy.com/es/courses/javascript-intermediate-en-757J2/0/5?curriculum_id=50ecb8d45f787a6332000042

http://www.codecademy.com/es/courses/web-beginner-en-seyrq/0/1?content_from=make-an-interactive-website%3Ajquery-effects

http://stackoverflow.com/questions/25274426/running-a-javascript-loop-inside-a-bootstrap-row

https://www.youtube.com/watch?v=fEYx8dQr_cQ

https://developers.google.com/youtube/v3/docs/?hl=es

https://developers.google.com/youtube/2.0/developers_guide_json

*/