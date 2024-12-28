from flask import Flask, request, send_file
from flask_cors import CORS
import subprocess
import os
import time

app = Flask(__name__)
CORS(app)

@app.route('/seamcarve', methods=['POST'])
def seamcarve():
    file = request.files['image']
    n_of_cols_to_reduce = int(request.form['n_of_cols_to_reduce'])
    n_of_rows_to_reduce = int(request.form['n_of_rows_to_reduce'])

    # Generate unique filenames
    timestamp = str(int(time.time()))
    input_filename = f'input_{timestamp}.jpg'
    output_filename = f'output_{timestamp}.jpg'

    # Save the image
    file.save(input_filename)
    
    # Call the C++ executable
    subprocess.run(['./seamcarving', input_filename, output_filename, str(n_of_cols_to_reduce), str(n_of_rows_to_reduce)])
    
    response = send_file(output_filename, mimetype='image/jpeg')
    
    # Delete the input and output files after processing
    os.remove(input_filename)
    os.remove(output_filename)
    
    return response

if __name__ == '__main__':
    app.run(debug=True)
