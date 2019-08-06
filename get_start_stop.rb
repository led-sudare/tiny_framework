# frozen_string_literal: true

require 'httpclient'
require 'json'

begin
  c = HTTPClient.new
  url = 'http://localhost:5004/api/status'
  res = c.get(url)
  status = JSON.parse(res.body)['enable']
  exit(status ? 0 : 1)
rescue StandardError => e
  p e
  exit(1)
end
