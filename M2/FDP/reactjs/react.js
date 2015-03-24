var converter = new Showdown.converter();
var curTag = "";
var Comment = React.createClass({
  render: function() {
	return (
	  <div className="comment">
		<h2 className="commentAuthor border-bottom-line">
		  {this.props.author}
		</h2>
		<img src={this.props.children.toString()} ></img>
	  </div>
	);
  }
});

var CommentBox = React.createClass({
 loadCommentsFromServer: function() {
 	var comments = this.state.data.tags;
	$.getJSON( this.props.url, {
	  url: this.props.url,
		tags: curTag,
		tagmode: "any",
		format: "json",
		dataType: 'json',
	}).done(function( data ) {
		this.setState({data: data.items});
		console.log(this);
	   // sate = {data:data};
	}.bind(this));
	  		//console.log(lesDatas);
  },
  handleCommentSubmit: function(comment) {
	$.getJSON( this.props.url, {
		url: this.props.url,
		tags: curTag,
		tagmode: "any",
		format: "json",
	  	dataType: 'json',
		type: 'POST',
	}).done(function( data ) {
		this.setState({data: data.items});
		console.log(this);
		// sate = {data:data};
	}.bind(this));
  },
  getInitialState: function() {
	return {data: [], tags:""};
  },
  componentDidMount: function() {
	this.loadCommentsFromServer();
	setInterval(this.loadCommentsFromServer, this.props.pollInterval);
  },
  render: function() {
	message = "tout";
	if(curTag.length != 0){
	  message = curTag;
	}
	return (
	  <div className="commentBox">
		<h1>Les photos de {message}</h1>
		<CommentList data={this.state.data} />
		<CommentForm onCommentSubmit={this.handleCommentSubmit} />
	  </div>
	);
  }
});

var CommentList = React.createClass({
  render: function() {
  console.log(this.props.data);
	var commentNodes = this.props.data.map(function(comment, index) {
	  return (
		<Comment author={comment.author} key={index}>
		  {comment.media.m}
		</Comment>
	  );
	});
	return (
	  <div className="commentList" >
		{commentNodes}
	  </div>
	);
  }
});

var CommentForm = React.createClass({
  handleSubmit: function(e) {
	e.preventDefault();
	var tags = this.refs.tags.getDOMNode().value.trim();
	if (!tags) {
	  curTag = "";
	} else {
	  curTag = tags;
	}
	this.props.onCommentSubmit({tags: tags});
	this.refs.tags.getDOMNode().value = '';
	return;
  },
  render: function() {
	return (
	  <form className="commentForm" onSubmit={this.handleSubmit}>
		<input type="text" placeholder="Tags" ref="tags" />
		<input type="submit" value="Post" />
	  </form>
	);
  }
});

React.render(
  <CommentBox url="http://api.flickr.com/services/feeds/photos_public.gne?jsoncallback=?" pollInterval={5000} />,
  document.getElementById('content')
);
