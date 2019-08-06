# frozen_string_literal: true

require 'sinatra'
require 'sinatra/reloader'
require 'json'

register Sinatra::Reloader
set :port, 5004
set :bind, '0.0.0.0'
status = true

get '/api/status' do
  content_type :json
  { enable: status }.to_json
end

post '/api/status' do
  p body = request.body.read
  p json = JSON.parse(body, symbolize_names: true)
  p status = json[:enable]
end
