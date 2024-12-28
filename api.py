from flask import Flask, request, send_file
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)

@app.route('/seamcarve', methods=['POST'])
def seamcarve():
    file = request.files['image']
    n_of_cols_to_reduce = int(request.form['n_of_cols_to_reduce'])
    n_of_rows_to_reduce = int(request.form['n_of_rows_to_reduce'])

    
    # Save the image
    file.save('input.jpg')
    
    # Call the C++ executable
    subprocess.run(['./seamcarving', 'input.jpg', 'output.jpg', str(n_of_cols_to_reduce), str(n_of_rows_to_reduce)])

    os.remove('input.jpg')
    
    return send_file('output.jpg', mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(debug=True)
