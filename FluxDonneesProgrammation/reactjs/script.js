var CommentBox = React.createClass({
  render: function() {
    return (
      <div className="commentBox">
        <h1>Comments</h1>
        Bonjour, le monde! Je suis un CommentBox.
        <commentList />
        <commentForm />
      </div>
    );
  }
});
React.render(
  <CommentBox />,
  document.getElementById('content')
);
var CommentList = React.createClass({
  render: function() {
    return (
      <div className="commentList">
        Bonjour, le monde! Je suis un CommentList.
      </div>
    );
  }
});

var CommentForm = React.createClass({
  render: function() {
    return (
      <div className="commentForm">
        Bonjour, le monde! Je suis un CommentForm.
      </div>
    );
  }
});
